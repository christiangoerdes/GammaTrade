import { useLocation } from "react-router-dom";
import { Link } from "react-router-dom";
import pages from "../../utils/pages";
import './Header.css';

const navLinks = Array.from(pages.values()).filter(page => page.anchorable);

export default function Header() {
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
                </ul>
            </nav>
        </header>
    )
}