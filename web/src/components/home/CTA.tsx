import { integrations } from './data'
import { useLanguage } from '../../i18n/LanguageContext'

export function CTA() {
    const { t } = useLanguage()

    return (
        <section className="cta-section">
            <h2>{t('cta.title')}</h2>
            <p className="subtitle">{t('cta.subtitle')}</p>
            <div className="cta-buttons">
                <a href="https://github.com/David-Imperium/Lex-compiler" className="btn btn-primary" target="_blank" rel="noopener noreferrer">
                    {t('cta.github')}
                </a>
                <a href="https://github.com/David-Imperium/Lex-compiler/releases" className="btn btn-secondary" target="_blank" rel="noopener noreferrer">
                    {t('cta.download')}
                </a>
                <a href="https://github.com/sponsors/David-Imperium" className="btn btn-sponsor" target="_blank" rel="noopener noreferrer">
                    {t('cta.sponsor')}
                </a>
            </div>
            <div className="links-row">
                {integrations.map((int, i) => (
                    <a key={i} href={int.url} target="_blank" rel="noopener noreferrer">
                        Link::{int.name}
                    </a>
                ))}
                <a href="https://github.com/David-Imperium/Lex-compiler/blob/master/docs/ROADMAP.md" target="_blank" rel="noopener noreferrer">
                    {t('cta.roadmap')}
                </a>
            </div>
        </section>
    )
}
