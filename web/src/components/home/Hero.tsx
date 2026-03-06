import { useLanguage } from '../../i18n/LanguageContext';

export function Hero() {
    const { t } = useLanguage();

    return (
        <section className="hero-section">
            <h1 className="glitch-text" data-text="LEX">LEX</h1>
            <p className="hero-tagline">{t('hero.tagline')}</p>
            <p className="hero-description">{t('hero.description')}</p>

            <div className="hero-actions">
                <a href="https://github.com/David-Imperium/Lex-compiler/releases" className="btn btn-primary" target="_blank" rel="noopener noreferrer">
                    {t('hero.download')}
                </a>
                <a href="https://github.com/David-Imperium/Lex-compiler#quick-start" className="btn btn-secondary" target="_blank" rel="noopener noreferrer">
                    {t('hero.docs')}
                </a>
            </div>

            <div className="hero-version">
                <span className="version status-pulse">{t('hero.status')}</span>
            </div>
        </section>
    )
}
