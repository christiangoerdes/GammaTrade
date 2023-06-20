import { useContext } from "react";
import { AuthContext } from "../../../utils/AuthContext";
import "./index.css";
import api from "../../../api/axiosConfig";

export default function Account() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    const handleLogout = () => {
        setLogInName(null);
        setLogInPassword(null);
        logout();
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
