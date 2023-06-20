import { useLocation } from "react-router-dom";
import { Link } from "react-router-dom";
import pages from "../../utils/pages";
import { useContext } from "react";
import { AuthContext } from "../../utils/AuthContext";
import './Header.css';

const navLinks = Array.from(pages.values()).filter(page => page.anchorable);

export default function Header() {
    const { isLoggedIn, login, logout, logInName, setLogInName, logInPassword, setLogInPassword } = useContext(AuthContext);
    
    const { pathname } = useLocation();

    return(
        <header>
            <nav className="container nav-bar">
                <Link to={ pages.get('home').path }>
                    <h1>Gamma Trade</h1>
                </Link>
                <ul className="nav-bar-links">
                    {navLinks.map((navLink, index) => 
                        <li key={index}>
                            <Link
                                className={ pathname === navLink.path ? 'current-location' : '' }
                                to={ navLink.path }
                            >
                                {navLink.name}
                            </Link>
                        </li>
                    )}
                    {!isLoggedIn 
                    ?
                        <li>
                            <Link 
                                className={ pages.get("login").path === pathname ? 'current-location' : '' }
                                to={ pages.get("login").path }
                            >
                                Login
                            </Link>
                        </li>
                    :
                        <li>
                            <Link 
                                className={ pages.get("account").path === pathname ? 'current-location' : '' }
                                to={ pages.get("account").path }
                            >
                                Account
                            </Link>
                        </li>
                    }
                </ul>
            </nav>
        </header>
    )
}