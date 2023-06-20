import { Route, Routes } from 'react-router-dom';
import pages from './utils/pages';
import Layout from './components/site-layout/Layout';

import Home from './components/pages/Home';
import Login from './components/pages/Login';
import ShopBuy from './components/pages/ShopBuy';
import ShopSell from './components/pages/ShopSell';

function App() {
	return (
		<Layout>
			<Routes>
				<Route
					path={ pages.get('home').path }
					element={ <Home /> }
				/>
				<Route
					path={ pages.get('login').path }
					element={ <Login /> }
				/>
				<Route
					path={ pages.get('shop-buy').path }
					element={ <ShopBuy /> }
				/>
				<Route
					path={ pages.get('shop-sell').path }
					element={ <ShopSell /> }
				/>
			</Routes>
		</Layout>
	);
}

export default App;
