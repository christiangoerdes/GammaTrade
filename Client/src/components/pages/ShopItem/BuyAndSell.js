import api from "../../../api/axiosConfig";
import { useEffect, useState } from "react";
import { useContext } from "react";
import { AuthContext } from "../../../utils/AuthContext";

export default function BuyAndSell(props) {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    const [amountOwnedStocks, setAmountOwnedStocks] = useState(null);
    const [amount, setAmount] = useState(0);

    const [success, setSuccess] = useState(false);
    
    const buyStocks = () => {
        api
        .get(`/buy-stocks?name=${logInName}&password=${logInPassword}&stock=DogeCoin&quantity=${amount}`)
        .then((response) => {
            console.log(response.data);
            if (response.data.success) {
                setSuccess((prevSuccess) => !prevSuccess)
            }
        })
    }
    const sellStocks = () => {
        api
        .get(`/sell-stocks?name=${logInName}&password=${logInPassword}&stock=DogeCoin&quantity=${amount}`)
        .then((response) => {
            console.log(response.data);
            if (response.data.success) {
                setSuccess((prevSuccess) => !prevSuccess)
            }
        })
    }

    useEffect(() => {
        api
        .get(`/get-stock?name=${logInName}&password=${logInPassword}&stock=${props.stock.toLowerCase()}`)
        .then((response) => {
            setAmountOwnedStocks(response.data.stock.amount);
        })
    }, [success])

    return(
        <>
            <div>Amount of your stocks {amountOwnedStocks}</div>
            <input 
                type="number"
                value={amount}
                min={0}
                onChange={e => setAmount(e.target.value)}
            />
            <button
                className="primary-button"
                onClick={buyStocks}
            >
                Buy Stocks
            </button>
            <button
                className="primary-button"
                onClick={sellStocks}
            >
                Sell Stocks
            </button>
        </>
    )
}
