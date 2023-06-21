import api from "../../../api/axiosConfig";
import { useLocation } from "react-router-dom";
import { useContext } from "react";
import { AuthContext } from "../../../utils/AuthContext";
import "./index.css";
import Graph from "./Graph";

export default function ShopItem() {
    const location = useLocation();
    
    return(
        <>
            <div className="shop-item-headline">
                <h2>{location.state.name}</h2>
            </div>
            <div className="container shop-item">
                <div className="shop-item-graph">
                    <Graph />
                </div>
                <div className="shop-item-info">
                    <span>{location.state.name}</span>
                    <span>some price</span>
                </div>
            </div>
        </>
    )
}
