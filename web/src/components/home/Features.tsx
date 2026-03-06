import { features } from './data'
import { useLanguage } from '../../i18n/LanguageContext'

export function Features() {
    const { t } = useLanguage()

    return (
        <section className="features-section">
            <h2>{t('features.title')}</h2>
            <div className="features-grid">
                {features.map((feature, i) => (
                    <div key={i} className="feature-card">
                        <div className="feature-icon">{feature.icon}</div>
                        <h3>{feature.title}</h3>
                        <p>{t(feature.descriptionKey!)}</p>
                    </div>
                ))}
            </div>
        </section>
    )
}
