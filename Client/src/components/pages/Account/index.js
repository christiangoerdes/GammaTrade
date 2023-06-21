import { useContext, useState } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../../../utils/AuthContext";
import "./index.css";
import api from "../../../api/axiosConfig";
import pages from "../../../utils/pages";
import Balance from "./Balance";

export default function Account() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    const navigate = useNavigate();

    const [amount, setAmount] = useState(0);
    const [errorMessage, setErrorMessage] = useState(null);

    const handleLogout = () => {
        setLogInName(null);
        setLogInPassword(null);
        logout();
        navigate(pages.get('login').path);
    }

    const handleDeposit = () => {
        api
        .get(`/deposit?name=${logInName}&password=${logInPassword}&amount=${amount}`)
        .then((response) => {
            console.log(response.data)
            if (response.data.success) {
                setErrorMessage(null);
            }
            else {
                setErrorMessage("Could not deposit");
            }
        })
    }
    const handleWithdraw = () => {
        api
        .get(`/withdraw?name=${logInName}&password=${logInPassword}&amount=${amount}`)
        .then((response) => {
            console.log(response.data);
            if (response.data.success) {
                setErrorMessage(null);
            }
            else {
                setErrorMessage("Could not withdraw");
            }
        })
    }

    const testItem = () => {
        const info = {
            name: "Dogecoin"
        }

        navigate(pages.get('shop-item').path, {state: info})
    }

    return(
        <>
            <div className="account-headline">
                <h2>Account</h2>
            </div>
            <div className="container logout">
                <h2>{logInName}</h2>
                
                <Balance />

                <div className="logout-balance-buttons">
                    <input
                        type="number"
                        value={amount}
                        min={0}
                        onChange={e => setAmount(e.target.value)}
                    />
                    <div>
                        <button 
                            className="primary-button"
                            onClick={handleDeposit}    
                        >
                            Deposit
                        </button>
                        <button 
                            className="primary-button"
                            onClick={handleWithdraw}    
                        >
                            Withdraw
                        </button>
                    </div>
                </div>
                {errorMessage && <span className="error-message">{errorMessage}</span>}

                <button
                    className="logout-button"
                    onClick={handleLogout}
                >
                    Logout
                </button>

                <button onClick={testItem}>Test Item</button>
            </div>
        </>
    )
}
