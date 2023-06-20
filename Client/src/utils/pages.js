const pages = new Map();

pages.set('home', { name: 'Home', path: '/', anchorable: true });

pages.set('shop-buy', { name: 'Shop Buy', path: '/shop-buy', anchorable: true });

pages.set('shop-sell', { name: 'Shop Sell', path: '/shop-sell', anchorable: true });

pages.set('login', { name: 'Login', path: '/login', anchorable: false });

pages.set('account', { name: 'Account', path: '/account', anchorable: false });

export default pages;
