const fs = require('fs');
const path = require('path');
const { minify } = require('terser');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Configuration
const sourceDir = __dirname;
const distDir = path.join(__dirname, 'dist');

// Obfuscation options (balanced for readability vs protection)
const obfuscatorOptions = {
    compact: true,
    controlFlowFlattening: false, // Keep false for better compatibility
    deadCodeInjection: false,
    debugProtection: false,
    debugProtectionInterval: 0,
    disableConsoleOutput: false,
    identifierNamesGenerator: 'hexadecimal',
    log: false,
    numbersToExpressions: false,
    renameGlobals: false,
    selfDefending: false,
    simplify: true,
    splitStrings: false,
    stringArray: true,
    stringArrayThreshold: 0.75,
    stringArrayIndexShift: true,
    stringArrayRotate: true,
    stringArrayShuffle: true,
    stringArrayWrappersCount: 1,
    stringArrayWrappersChainedCalls: true,
    stringArrayWrappersParametersMaxCount: 2,
    stringArrayWrappersType: 'variable',
    stringArrayEncoding: ['base64'],
    target: 'browser',
    unicodeEscapeSequence: false
};

// Create dist directory
if (!fs.existsSync(distDir)) {
    fs.mkdirSync(distDir);
}

// Create subdirectories
const subdirs = ['css', 'js', 'js/games'];
subdirs.forEach(dir => {
    const fullPath = path.join(distDir, dir);
    if (!fs.existsSync(fullPath)) {
        fs.mkdirSync(fullPath, { recursive: true });
    }
});

console.log('🚀 Starting build process...\n');

// Copy and process CSS files
console.log('📄 Copying CSS files...');
fs.copyFileSync(
    path.join(sourceDir, 'css', 'styles.css'),
    path.join(distDir, 'css', 'styles.css')
);
console.log('✅ CSS files copied\n');

// Minify and obfuscate JavaScript files
console.log('🔧 Minifying and obfuscating JavaScript files...');

const jsFiles = [
    { src: 'js/base.js', dest: 'js/base.min.js' },
    { src: 'js/main.js', dest: 'js/main.min.js' },
    { src: 'js/home.js', dest: 'js/home.min.js' },
    { src: 'js/games/tictactoe.js', dest: 'js/games/tictactoe.min.js' },
    { src: 'js/games/fourinarow.js', dest: 'js/games/fourinarow.min.js' },
    { src: 'js/games/numerical.js', dest: 'js/games/numerical.min.js' },
    { src: 'js/games/sus.js', dest: 'js/games/sus.min.js' },
    { src: 'js/games/misere.js', dest: 'js/games/misere.min.js' },
    { src: 'js/games/word.js', dest: 'js/games/word.min.js' },
    { src: 'js/games/4x4.js', dest: 'js/games/4x4.min.js' },
    { src: 'js/games/5x5.js', dest: 'js/games/5x5.min.js' },
    { src: 'js/games/obstacle.js', dest: 'js/games/obstacle.min.js' },
    { src: 'js/games/diamond.js', dest: 'js/games/diamond.min.js' },
    { src: 'js/games/timed.js', dest: 'js/games/timed.min.js' }
];

async function processJSFiles() {
    for (const file of jsFiles) {
        const srcPath = path.join(sourceDir, file.src);
        const destPath = path.join(distDir, file.dest);
        
        try {
            // Read source file
            const code = fs.readFileSync(srcPath, 'utf8');
            
            // First minify with Terser
            const minified = await minify(code, {
                compress: {
                    dead_code: true,
                    drop_console: false, // Keep console for debugging if needed
                    drop_debugger: true,
                    keep_classnames: true,
                    keep_fnames: true
                },
                mangle: {
                    keep_classnames: true,
                    keep_fnames: true
                },
                format: {
                    comments: false
                }
            });
            
            // Then obfuscate
            const obfuscated = JavaScriptObfuscator.obfuscate(minified.code, obfuscatorOptions);
            
            // Write to destination
            fs.writeFileSync(destPath, obfuscated.getObfuscatedCode());
            
            const originalSize = Buffer.byteLength(code, 'utf8');
            const minifiedSize = Buffer.byteLength(obfuscated.getObfuscatedCode(), 'utf8');
            const reduction = ((1 - minifiedSize / originalSize) * 100).toFixed(1);
            
            console.log(`✅ ${file.src} → ${file.dest} (${reduction}% reduction)`);
        } catch (error) {
            console.error(`❌ Error processing ${file.src}:`, error.message);
        }
    }
}

// Copy and update HTML files
function updateHTMLFiles() {
    console.log('\n📄 Processing HTML files...');
    
    // Process index.html
    let indexHTML = fs.readFileSync(path.join(sourceDir, 'index.html'), 'utf8');
    indexHTML = indexHTML.replace('js/home.js', 'js/home.min.js');
    fs.writeFileSync(path.join(distDir, 'index.html'), indexHTML);
    console.log('✅ index.html processed');
    
    // Process game.html
    let gameHTML = fs.readFileSync(path.join(sourceDir, 'game.html'), 'utf8');
    gameHTML = gameHTML.replace('js/base.js', 'js/base.min.js');
    gameHTML = gameHTML.replace('js/games/tictactoe.js', 'js/games/tictactoe.min.js');
    gameHTML = gameHTML.replace('js/games/fourinarow.js', 'js/games/fourinarow.min.js');
    gameHTML = gameHTML.replace('js/games/numerical.js', 'js/games/numerical.min.js');
    gameHTML = gameHTML.replace('js/games/sus.js', 'js/games/sus.min.js');
    gameHTML = gameHTML.replace('js/games/misere.js', 'js/games/misere.min.js');
    gameHTML = gameHTML.replace('js/games/word.js', 'js/games/word.min.js');
    gameHTML = gameHTML.replace('js/games/4x4.js', 'js/games/4x4.min.js');
    gameHTML = gameHTML.replace('js/games/5x5.js', 'js/games/5x5.min.js');
    gameHTML = gameHTML.replace('js/games/obstacle.js', 'js/games/obstacle.min.js');
    gameHTML = gameHTML.replace('js/games/diamond.js', 'js/games/diamond.min.js');
    gameHTML = gameHTML.replace('js/games/timed.js', 'js/games/timed.min.js');
    gameHTML = gameHTML.replace('js/main.js', 'js/main.min.js');
    fs.writeFileSync(path.join(distDir, 'game.html'), gameHTML);
    console.log('✅ game.html processed');
}

// Run the build
processJSFiles().then(() => {
    updateHTMLFiles();
    console.log('\n✨ Build complete! Files ready in ./dist directory');
    console.log('📦 Production-ready files are minified and obfuscated\n');
}).catch(error => {
    console.error('❌ Build failed:', error);
    process.exit(1);
});


