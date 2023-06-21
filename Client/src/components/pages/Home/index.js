import './index.css';
import { useState, useContext } from 'react';
import { AuthContext } from '../../../utils/AuthContext';

export default function Home() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    return(
        <>
            <div className="home-headline">
                <h2>Home</h2>
            </div>
        </>
    )
}