import "./index.css";
import { useState, useContext } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../../../utils/AuthContext";
import api from "../../../api/axiosConfig";
import pages from "../../../utils/pages";

export default function Login() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);

    const navigate = useNavigate();

    const [hasAccount, setHasAccount] = useState(true);
    const [name, setName] = useState("");
    const [password, setPassword] = useState("");

    const [errorMessage, setErrorMessage] = useState(null);

    const nameValid = () => {return name.length !== 0}
    const passwordValid = () => {return password.length !== 0}
    const allFieldsValid = () => {return nameValid && passwordValid}

    const handleFormSubmit = (e) => {
        e.preventDefault();
        /* Log in Logic */
        if (hasAccount) {
            api
            .get(`/login?name=${name}&password=${password}`)
            .then((response) => {
                console.log(response.data)
                if (response.data.status === "login successful") {
                    setLogInName(name);
                    setLogInPassword(password);
                    setErrorMessage(null);
                    login();
                    navigate(pages.get('account').path);
                }
                else if (response.data.status === "wrong password") {
                    setErrorMessage("Wrong Password! Please try again.");
                }
                else {
                    setErrorMessage("User not found.")
                }
            })
        }
        /* Sign Up Logic */
        else {
            api
            .get(`/sign-up?name=${name}&password=${password}`)
            .then((response) => {
                console.log(response.data)
                if (response.data.success) {
                    setLogInName(name);
                    setLogInPassword(password);
                    setErrorMessage(null);
                    login();
                }
                else {
                    setErrorMessage("The User(name) already exists!");
                }
            })
        }
    }

    const hasAccountToString = (pHasAccount) => {
        if (pHasAccount) {
            return "Log in";
        }
        else {
            return "Sign up";
        }
    }
    const handleHasAccountToggle = () => {
        setHasAccount((current) => !current);
    }

    return(
        <>
            <div className="login-headline">
                <h2>{hasAccountToString(hasAccount)}</h2>
            </div>
            <div className="container login">
                <form onSubmit={handleFormSubmit}>
                    <label htmlFor="name">Name</label>
                    <input 
                        type="text"
                        id="name"
                        value={name}
                        onChange={e => setName(e.target.value)}
                    />
                    <label htmlFor="password">Password</label>
                    <input 
                        type="password"
                        id="password"
                        value={password}
                        onChange={e => setPassword(e.target.value)}
                    />
                    <button
                        className="primary-button"
                        type="submit"
                        disabled={!allFieldsValid}
                    >
                        {hasAccountToString(hasAccount)}
                    </button>
                    {errorMessage
                    ?
                    <span className="error-message">
                        {errorMessage}
                    </span>
                    :
                    <></>
                    }
                    <span className="has-account">
                        Want to <span onClick={handleHasAccountToggle} className="has-account-click">{hasAccountToString(!hasAccount)}</span> instead?
                    </span>
                </form>
            </div>
        </>
    )
}