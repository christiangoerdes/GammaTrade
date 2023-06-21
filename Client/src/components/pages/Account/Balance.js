import { useState, useEffect } from "react";
import { useContext } from "react";
import { AuthContext } from "../../../utils/AuthContext";
import api from "../../../api/axiosConfig";

export default function Balance() {
    const [balance, setBalance] = useState(0);
    
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);

    const getBalance = async () => {
        try {
            const response = await api.get(`/get-my-balance?name=${logInName}&password=${logInPassword}`);
            setBalance(response.data.balance)
        }
        catch(err) {
            console.log(err);
        }
    }

    useEffect(() => {
        const interval = setInterval(getBalance, 500);

        return () => {
            clearInterval(interval);
        }
    })

    return(
            <span>Balance ${balance.toString()}</span>
    )
}
