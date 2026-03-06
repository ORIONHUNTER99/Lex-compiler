import { backends } from './data'
import { useLanguage } from '../../i18n/LanguageContext'

export function Backends() {
    const { t } = useLanguage()

    return (
        <section className="backends-section">
            <h2>{t('backends.title')}</h2>
            <p className="subtitle">{t('backends.subtitle')}</p>
            <div className="backends-grid">
                {backends.map((backend, i) => (
                    <div key={i} className="backend-card">
                        <div className="backend-icon">{backend.icon}</div>
                        <div className="backend-name">{backend.name}</div>
                        <div className="backend-target">{t(backend.targetKey!)}</div>
                    </div>
                ))}
            </div>
        </section>
    )
}
