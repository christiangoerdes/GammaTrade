import { useEffect, useState } from "react";
import api from "../../../api/axiosConfig";

export default function ItemNamePrice(props) {
    const [name, setName] = useState("");
    const [price, setPrice] = useState(0);
    
    const getItemData = () => {
        api
        .get(`/get-stock-logged-out?stock=${props.stock.toLowerCase()}`)
        .then((response) => {
            setName(response.data.stock.name);
            setPrice(response.data.stock.price);
        })
    }

    useEffect(() => {
        const interval = setInterval(getItemData, 1500);

        return () => {
            clearInterval(interval);
        }
    })

    return(
        <>
            <div>Name: {name}</div>
            <div>Price: {price.toFixed(2)}</div>
        </>
    )
}
