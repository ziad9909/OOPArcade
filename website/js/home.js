/**
 * home.js
 * Home page functionality with animations
 */

document.addEventListener('DOMContentLoaded', () => {
    // Add hover animations to game cards
    const gameCards = document.querySelectorAll('.game-card');
    
    gameCards.forEach(card => {
        card.addEventListener('mouseenter', () => {
            // Optional: Add sound effect or additional animation
        });
    });

    // Add fade-in animation on load
    const header = document.querySelector('.header');
    const gamesGrid = document.querySelector('.games-grid');
    
    if (header) {
        header.style.opacity = '0';
        header.style.transform = 'translateY(-20px)';
        
        setTimeout(() => {
            header.style.transition = 'all 0.8s ease';
            header.style.opacity = '1';
            header.style.transform = 'translateY(0)';
        }, 100);
    }

    if (gamesGrid) {
        const cards = gamesGrid.querySelectorAll('.game-card');
        cards.forEach((card, index) => {
            card.style.opacity = '0';
            card.style.transform = 'translateY(30px)';
            
            setTimeout(() => {
                card.style.transition = 'all 0.5s ease';
                card.style.opacity = '1';
                card.style.transform = 'translateY(0)';
            }, 200 + (index * 50));
        });
    }

    // Add particle effect to title (optional enhancement)
    createTitleEffect();
});

/**
 * Create a subtle particle effect for the title
 */
function createTitleEffect() {
    const title = document.querySelector('.title');
    
    if (!title) return;

    // Add shimmer effect
    title.style.position = 'relative';
    title.style.overflow = 'hidden';

    // Optional: You can add more advanced effects here
}

/**
 * Handle game card clicks with smooth transition
 */
function navigateToGame(gameType) {
    const card = document.querySelector(`[data-game="${gameType}"]`);
    
    if (card) {
        card.style.transform = 'scale(0.95)';
        
        setTimeout(() => {
            window.location.href = `game.html?game=${gameType}`;
        }, 200);
    }
}

// Expose to window
window.navigateToGame = navigateToGame;

