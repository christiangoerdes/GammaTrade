import ItemCard from "./ItemCard";
import "./index.css";

export default function Shop() {
    
    
    return(
        <>
            <div className="shop-headline">
                <h2>Shop</h2>
            </div>
            <div className="container shop">
                <ItemCard stock={"DogeCoin"} />
            </div>
        </>
    )
}