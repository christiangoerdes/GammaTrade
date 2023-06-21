const pages = new Map();

pages.set('home', { name: 'Home', path: '/', anchorable: true });

pages.set('shop', { name: 'Shop', path: '/shop', anchorable: true });

pages.set('login', { name: 'Login', path: '/login', anchorable: false });

pages.set('account', { name: 'Account', path: '/account', anchorable: false });

export default pages;
