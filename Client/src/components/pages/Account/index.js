import { useContext, useState } from "react";
import { useNavigate } from "react-router-dom";
import { AuthContext } from "../../../utils/AuthContext";
import "./index.css";
import api from "../../../api/axiosConfig";
import pages from "../../../utils/pages";

export default function Account() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    const navigate = useNavigate();

    const [balance, setBalance] = useState(null);
    const [amount, setAmount] = useState(0);
    const [errorMessage, setErrorMessage] = useState(null);

    const getBalance = () => {
        api
        .get(`/get-my-balance?name=${logInName}&password=${logInPassword}`)
        .then((response) => {
            setBalance(response.data.balance);
        })
    }

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

    return(
        <>
            <div className="account-headline">
                <h2>Account</h2>
            </div>
            <div className="container logout">
                <h2>{logInName}</h2>
                
                <span className="logout-balance">Current Balance: ${balance ? balance : ""}</span>

                <button onClick={getBalance}>Update Balance</button>

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
            </div>
        </>
    )
}
