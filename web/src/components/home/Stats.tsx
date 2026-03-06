import { stats } from './data'
import { useLanguage } from '../../i18n/LanguageContext'

export function Stats() {
    const { t } = useLanguage()

    return (
        <section className="stats-section">
            <div className="stats-grid">
                {stats.map((stat, i) => (
                    <div key={i} className="stat-card">
                        <div className="stat-number">{stat.value}</div>
                        <div className="stat-label">{t(stat.labelKey!)}</div>
                    </div>
                ))}
            </div>
        </section>
    )
}
