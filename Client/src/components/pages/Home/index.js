import './index.css';
import { useState, useContext } from 'react';
import { AuthContext } from '../../../utils/AuthContext';
import ItemCard from "../Shop/ItemCard";

export default function Home() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    return(
        <>
            <div className="home-headline">
                <h2>Market</h2>
            </div>
            <div className='container home'>
                    <p className='home-heading'>
                        Hottest Stocks!!!
                    </p>
                    <div className='home-stocks'>
                        <ItemCard stock={"DogeCoin"} />
                        <ItemCard stock={"RedPanda Retail"} />
                        <ItemCard stock={"Quantum Computing Inc"} />
                    </div>
            </div>
        </>
    )
}