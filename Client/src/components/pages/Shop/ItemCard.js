import api from "../../../api/axiosConfig";
import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import pages from "../../../utils/pages";

export default function ItemCard(props) {
    const [price, setPrice] = useState(0);

    const navigate = useNavigate();

    const goToItem = () => {
        const info = {
            name: props.stock
        }

        navigate(pages.get('shop-item').path, {state: info})
    }

    const getData = () => {
        api
        .get(`/get-stock-logged-out?stock=${props.stock.toLowerCase()}`)
        .then((response) => {
            setPrice(response.data.stock.price);
        })
    }

    useEffect(() => {
        const interval = setInterval(getData, 1000);

        return () => {
            clearInterval(interval);
        }
    })

    /* useEffect(() => {
        api
        .get(`/get-stock-logged-out?stock=${props.stock}`)
        .then((response) => {
            setPrice(response.data.stock.price);
        })
    }, []) */

    return(
        <div className="item-card" onClick={goToItem}>
            <span>{props.stock}</span>
            <span>${price.toFixed(2)}</span>
        </div>
    )
}