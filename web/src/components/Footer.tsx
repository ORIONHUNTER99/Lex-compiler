import { Link } from 'react-router-dom';
import { useLanguage } from '../i18n/LanguageContext';

export default function Footer() {
    const { t } = useLanguage();

    return (
        <footer className="advanced-footer">
            <div className="footer-container">
                <div className="footer-grid">

                    <div className="footer-column brand-column">
                        <div className="brand-lex">LEX<span className="brand-dot">.</span></div>
                        <p className="footer-tagline">{t('footer.tagline1')}<br />{t('footer.tagline2')}</p>
                        <div className="system-status">
                            <span className="status-dot"></span>
                            {t('hero.status')}
                        </div>
                    </div>

                    <div className="footer-column">
                        <h3>{t('footer.resources')}</h3>
                        <Link to="/docs">{t('nav.docs')}</Link>
                        <a href="https://github.com/David-Imperium/Lex-compiler/blob/master/docs/TUTORIAL.md" target="_blank" rel="noopener noreferrer">{t('footer.tutorial')}</a>
                        <a href="https://github.com/David-Imperium/Lex-compiler/blob/master/docs/API_REFERENCE.md" target="_blank" rel="noopener noreferrer">{t('footer.apiRef')}</a>
                        <Link to="/playground">{t('nav.playground')}</Link>
                    </div>

                    <div className="footer-column">
                        <h3>{t('footer.project')}</h3>
                        <a href="https://github.com/David-Imperium/Lex-compiler/releases" target="_blank" rel="noopener noreferrer">{t('footer.releases')}</a>
                        <a href="https://github.com/David-Imperium/Lex-compiler/blob/master/docs/ROADMAP.md" target="_blank" rel="noopener noreferrer">{t('footer.roadmap')}</a>
                        <a href="https://github.com/David-Imperium/Lex-compiler/issues" target="_blank" rel="noopener noreferrer">{t('footer.issues')}</a>
                        <a href="https://opensource.org/licenses/MIT" target="_blank" rel="noopener noreferrer">{t('footer.license')}</a>
                    </div>

                    <div className="footer-column">
                        <h3>{t('footer.community')}</h3>
                        <a href="https://github.com/David-Imperium/Lex-compiler" target="_blank" rel="noopener noreferrer">{t('footer.repo')}</a>
                        <a href="https://github.com/sponsors/David-Imperium" className="sponsor-link" target="_blank" rel="noopener noreferrer">
                            {t('footer.sponsor')}
                        </a>
                    </div>

                </div>

                <div className="footer-bottom">
                    <div className="copyright">
                        © {new Date().getFullYear()} {t('footer.rights')}
                    </div>
                    <div className="build-info">
                        BUILD: v1.0.0 // TGT: MULTI
                    </div>
                </div>
            </div>
        </footer>
    );
}
