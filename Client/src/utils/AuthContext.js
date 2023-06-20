import { createContext, useState } from "react";

const AuthContext = createContext();

const AuthProvider = ({ children }) => {
    const [isLoggedIn, setIsLoggedIn] = useState(false);
    const [logInName, setLogInName] = useState(null);
    const [logInPassword, setLogInPassword] = useState(null);

    const login = () => setIsLoggedIn(true);
    const logout = () => setIsLoggedIn(false);

    return (
        <AuthContext.Provider value={ {isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword} }>
            {children}
        </AuthContext.Provider>
    )
}

export { AuthContext, AuthProvider };