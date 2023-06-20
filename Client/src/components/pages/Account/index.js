import { useContext } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../../../utils/AuthContext";
import "./index.css";
import api from "../../../api/axiosConfig";
import pages from "../../../utils/pages";

export default function Account() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    const navigate = useNavigate();

    const handleLogout = () => {
        setLogInName(null);
        setLogInPassword(null);
        logout();
        navigate(pages.get('login').path);
    }

    return(
        <>
            <div className="account-headline">
                <h2>Account</h2>
            </div>
            <div className="container logout">
                <button 
                    className="primary-button"
                    onClick={handleLogout}
                >
                    Logout
                </button>
            </div>
        </>
    )
}
