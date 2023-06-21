import api from "../../../api/axiosConfig";
import { useEffect, useState } from "react";
import { AuthContext } from "../../../utils/AuthContext";
import { useContext } from "react";
import ItemCard from "../Shop/ItemCard";

export default function MyStocks() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);

    const [data, setData] = useState(null);

    useEffect(() => {
        api
        .get(`/get-stocks?name=${logInName}&password=${logInPassword}`)
        .then((response) => {
            console.log(response.data.stocks.filter(item => item.amount !== 0));
            setData(response.data.stocks.filter(item => item.amount !== 0));
        })
    }, [])

    return(
        <>
            {data && <div className="container logout">
                <span>My Stocks</span>
                {data.map((item, index) =>
                    <ItemCard stock={item.name} />    
                )}
            </div>}
        </>
    )
}
