import { Route, Routes } from 'react-router-dom';
import pages from './utils/pages';
import Layout from './components/site-layout/Layout';

import Home from './components/pages/Home';
import Login from './components/pages/Login';
import Account from './components/pages/Account';
import Shop from './components/pages/Shop';

import { AuthProvider } from './utils/AuthContext';

function App() {
	return (
		<AuthProvider>
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
						path={ pages.get('account').path }
						element={ <Account /> }
					/>
					<Route
						path={ pages.get('shop').path }
						element={ <Shop /> }
					/>
				</Routes>
			</Layout>
		</AuthProvider>
	);
}

export default App;
