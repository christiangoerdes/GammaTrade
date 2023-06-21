import api from "../../../api/axiosConfig";
import { useState } from "react";
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

    return(
        <div className="item-card" onClick={goToItem}>
            <span>{props.stock}</span>
            <span>$5</span>
        </div>
    )
}