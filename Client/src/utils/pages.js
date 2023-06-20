const pages = new Map();

pages.set('home', { name: 'Home', path: '/', anchorable: true });

pages.set('shop-buy', { name: 'Shop Buy', path: '/shop-buy', anchorable: true });

pages.set('shop-sell', { name: 'Shop Sell', path: '/shop-sell', anchorable: true });

pages.set('login', { name: 'Login', path: '/login', anchorable: false });

pages.set('logout', { name: 'Logout', path: '/logout', anchorable: false });

export default pages;
