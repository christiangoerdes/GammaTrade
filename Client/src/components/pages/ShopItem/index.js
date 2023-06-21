import api from "../../../api/axiosConfig";
import { useLocation } from "react-router-dom";
import { useContext } from "react";
import { AuthContext } from "../../../utils/AuthContext";
import "./index.css";
import Graph from "./Graph";
import ItemNamePrice from "./ItemNamePrice";
import BuyAndSell from "./BuyAndSell";

export default function ShopItem() {
    const location = useLocation();
    
    return(
        <>
            <div className="shop-item-headline">
                <h2>{location.state.name}</h2>
            </div>
            <div className="container shop-item">
                <div className="shop-item-graph">
                    <Graph stock={location.state.name}/>
                </div>
                <div className="shop-item-info">
                    <div>
                        <ItemNamePrice stock={location.state.name} />
                    </div>
                    <div>
                        {/* Only if logged in!! */}
                        <BuyAndSell stock={location.state.name} />
                    </div>
                </div>
            </div>
        </>
    )
}
