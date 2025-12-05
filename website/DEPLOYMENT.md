# 🚀 Deployment Guide - OOP Arcade

Complete step-by-step deployment instructions for various platforms.

## 📋 Pre-Deployment Checklist

- [ ] All games tested and working
- [ ] Files are in the correct structure
- [ ] No broken links or missing files
- [ ] Responsive design tested on different screen sizes
- [ ] Browser compatibility verified

## 🌐 Deployment Options

### Option 1: Netlify (Easiest - Recommended)

#### Method A: Drag & Drop (2 minutes)

1. **Visit Netlify Drop**
   - Go to: https://app.netlify.com/drop

2. **Drag the folder**
   - Open your file explorer
   - Locate the `website` folder
   - Drag it onto the Netlify Drop page

3. **Done!**
   - Your site will be live immediately
   - You'll get a URL like: `https://random-name-123.netlify.app`
   - Click "Claim site" to customize the URL

#### Method B: Git Integration (Best for updates)

1. **Create GitHub Repository**
   ```bash
   cd website
   git init
   git add .
   git commit -m "Initial commit: OOP Arcade"
   git branch -M main
   ```

2. **Push to GitHub**
   ```bash
   # Create a new repository on GitHub first, then:
   git remote add origin https://github.com/YOUR_USERNAME/oop-arcade.git
   git push -u origin main
   ```

3. **Connect to Netlify**
   - Go to: https://app.netlify.com
   - Click "Add new site" → "Import an existing project"
   - Choose "GitHub" and authorize
   - Select your repository
   - Build settings:
     - Build command: (leave empty)
     - Publish directory: `.` or leave empty
   - Click "Deploy site"

4. **Custom Domain (Optional)**
   - Go to Site settings → Domain management
   - Click "Add custom domain"
   - Follow DNS configuration instructions

#### Netlify Configuration (Optional)

Create `netlify.toml` in the website folder:

```toml
[build]
  publish = "."

[[redirects]]
  from = "/*"
  to = "/index.html"
  status = 200
```

---

### Option 2: GitHub Pages (Free)

1. **Create Repository**
   ```bash
   cd website
   git init
   git add .
   git commit -m "Initial commit"
   git branch -M main
   ```

2. **Push to GitHub**
   ```bash
   # Create repo on GitHub first
   git remote add origin https://github.com/YOUR_USERNAME/oop-arcade.git
   git push -u origin main
   ```

3. **Enable GitHub Pages**
   - Go to repository Settings
   - Scroll to "Pages" section
   - Source: "Deploy from a branch"
   - Branch: `main` → `/` (root)
   - Click "Save"

4. **Access Your Site**
   - URL: `https://YOUR_USERNAME.github.io/oop-arcade/`
   - Wait 2-3 minutes for first deployment

**Note:** GitHub Pages may take a few minutes to update on changes.

---

### Option 3: Vercel (Fast)

1. **Install Vercel CLI**
   ```bash
   npm install -g vercel
   ```

2. **Deploy**
   ```bash
   cd website
   vercel
   ```

3. **Follow Prompts**
   - Login/Sign up
   - Confirm project settings
   - Deploy!

4. **Your site is live!**
   - You'll get a URL like: `https://oop-arcade.vercel.app`

---

### Option 4: Firebase Hosting

1. **Install Firebase CLI**
   ```bash
   npm install -g firebase-tools
   ```

2. **Login to Firebase**
   ```bash
   firebase login
   ```

3. **Initialize Project**
   ```bash
   cd website
   firebase init hosting
   ```
   - Select: Create a new project or use existing
   - Public directory: `.` (current directory)
   - Configure as single-page app: No
   - Set up automatic builds: No

4. **Deploy**
   ```bash
   firebase deploy
   ```

5. **Access Your Site**
   - URL: `https://YOUR_PROJECT_ID.web.app`

---

### Option 5: Surge.sh (Simple)

1. **Install Surge**
   ```bash
   npm install -g surge
   ```

2. **Deploy**
   ```bash
   cd website
   surge
   ```

3. **Follow Prompts**
   - Email/Password (first time only)
   - Project path: . (press Enter)
   - Domain: Choose a name or use suggested

4. **Done!**
   - URL: `https://your-chosen-name.surge.sh`

---

### Option 6: Traditional Web Hosting (cPanel)

1. **Prepare Files**
   - Zip the entire `website` folder contents

2. **Upload via FTP or cPanel**
   - Login to your hosting control panel
   - Navigate to `public_html` or `www`
   - Upload all files from the website folder
   - Extract if uploaded as zip

3. **Set Permissions**
   ```
   Files: 644
   Folders: 755
   ```

4. **Access Your Site**
   - URL: `https://yourdomain.com`

---

## 🔒 Security Considerations

### CSP Headers (Optional)

Add to your hosting configuration:

```
Content-Security-Policy: default-src 'self'; script-src 'self' 'unsafe-inline'; style-src 'self' 'unsafe-inline';
```

### HTTPS

- Netlify, Vercel, GitHub Pages: Automatic HTTPS ✅
- Traditional hosting: Configure SSL certificate

---

## 🎯 Post-Deployment Checklist

- [ ] Open the site in multiple browsers
- [ ] Test all 11 games
- [ ] Try different screen sizes (responsive test)
- [ ] Check all player modes (Human, Random AI, Smart AI)
- [ ] Verify restart button works
- [ ] Test back button to home page
- [ ] Check console for any errors

---

## 📊 Performance Optimization

### Before Deployment

1. **Minify CSS** (Optional)
   ```bash
   # Using online tool or CLI
   npx clean-css-cli -o styles.min.css styles.css
   ```

2. **Minify JavaScript** (Optional)
   ```bash
   # Using terser
   npx terser base.js -o base.min.js
   ```

3. **Compress Images** (if you add any)
   - Use TinyPNG, ImageOptim, or similar

### Caching Headers

For better performance, configure caching:

**Netlify** (`netlify.toml`):
```toml
[[headers]]
  for = "/*"
  [headers.values]
    Cache-Control = "public, max-age=31536000"
```

**Vercel** (`vercel.json`):
```json
{
  "headers": [
    {
      "source": "/(.*)",
      "headers": [
        {
          "key": "Cache-Control",
          "value": "public, max-age=31536000"
        }
      ]
    }
  ]
}
```

---

## 🐛 Troubleshooting

### Issue: Games not loading

**Solution:**
- Check browser console for errors
- Ensure all JS files are loaded correctly
- Verify file paths are correct

### Issue: Blank page after deployment

**Solution:**
- Check that index.html is in the root of deployment folder
- Verify all relative paths are correct
- Check browser console for 404 errors

### Issue: AI not working

**Solution:**
- Ensure all game JS files are loaded before main.js
- Check that base.js loads first
- Verify no JavaScript errors in console

### Issue: Styles not applying

**Solution:**
- Check CSS file path in HTML
- Clear browser cache
- Verify CSS file was uploaded correctly

---

## 🔄 Updating Your Site

### Netlify (Git)
```bash
git add .
git commit -m "Update: description"
git push origin main
# Automatic deployment!
```

### GitHub Pages
```bash
git add .
git commit -m "Update: description"
git push origin main
# Wait 2-3 minutes for update
```

### Vercel
```bash
vercel --prod
# Or push to git if connected
```

### Surge
```bash
surge
# Same domain as before
```

---

## 📱 Testing URLs

After deployment, test on:

- [BrowserStack](https://www.browserstack.com/live) - Multiple devices
- [Responsively App](https://responsively.app/) - Responsive testing
- [Google Mobile-Friendly Test](https://search.google.com/test/mobile-friendly)

---

## 🎉 Success!

Your OOP Arcade is now live! Share your URL:

```
🎮 Check out my Board Games Collection:
[Your URL here]

Features:
- 11 Classic Games
- Smart AI Opponents
- Beautiful UI
- No Frameworks!
```

---

## 📞 Support

If you encounter any issues:

1. Check browser console for errors
2. Verify all files are uploaded
3. Try different browser
4. Clear cache and reload
5. Check deployment platform documentation

---

**Happy Deploying! 🚀**

