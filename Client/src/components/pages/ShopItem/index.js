import api from "../../../api/axiosConfig";
import { useLocation } from "react-router-dom";
import { useContext } from "react";
import { AuthContext } from "../../../utils/AuthContext";

export default function ShopItem() {
    const location = useLocation();
    
    return(
        <>
            {/* <span>{location.state.name}</span> */}
            <div className="shop-item">
                
            </div>
        </>
    )
}
