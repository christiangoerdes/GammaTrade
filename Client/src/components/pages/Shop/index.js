import ItemCard from "./ItemCard";
import "./index.css";
import { useEffect, useState } from "react";
import api from "../../../api/axiosConfig";

export default function Shop() {
    const [data, setData] = useState(null);
    
    useEffect(() => {
        api
        .get(`/get-stocks-logged-out`)
        .then((response) => {
            console.log(response.data.stocks);
            setData(response.data.stocks);
        })
    }, [])

    return(
        <>
            <div className="shop-headline">
                <h2>Shop</h2>
            </div>
            {data && <div className="container shop">
            {data.map((item, index) =>
                <ItemCard stock={item.name} />    
            )}
            </div>}
            {!data && <div className="container shop">Loading Items...</div>}
        </>
    )
}