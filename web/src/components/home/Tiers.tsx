import { useLanguage } from '../../i18n/LanguageContext'

export function Tiers() {
    const { t } = useLanguage();

    const tiersData = [
        {
            name: t('tiers.base.name'),
            price: t('tiers.base.price'),
            period: t('tiers.base.period'),
            description: t('tiers.base.desc'),
            // We know features is an array, but t() signature is string. To avoid TS errors, we map over a fixed number or just cast it if we loosen LanguageContext.
            // Let's use the dictionary directly via context since we have access to it, or just use hardcoded english for this array for a sec.
            // Wait, I can just cast the generic `t('tiers.base.features')` as any to an array of strings.
            features: t('tiers.base.features') as unknown as string[],
            highlighted: false,
            cta: t('tiers.base.cta'),
            ctaLink: 'https://github.com/David-Imperium/Lex-compiler',
        },
        {
            name: t('tiers.core.name'),
            price: t('tiers.core.price'),
            period: t('tiers.core.period'),
            description: t('tiers.core.desc'),
            features: t('tiers.core.features') as unknown as string[],
            highlighted: true,
            cta: t('tiers.core.cta'),
            ctaLink: 'https://github.com/sponsors/David-Imperium',
        },
    ];

    return (
        <section className="tiers-section">
            <h2>{t('tiers.title')}</h2>
            <p className="subtitle">{t('tiers.subtitle')}</p>

            <div className="tiers-grid">
                {tiersData.map((tier, i) => (
                    <div key={i} className={`tier-card ${tier.highlighted ? 'highlighted' : ''}`}>
                        {tier.highlighted && <div className="tier-badge">{t('tiers.earlyBird')}</div>}
                        <div className="tier-header">
                            <h3 className="tier-name">{tier.name}</h3>
                            <div className="tier-price">
                                <span className="price">{tier.price}</span>
                                {tier.period && <span className="period">/{tier.period}</span>}
                            </div>
                            <p className="tier-description">{tier.description}</p>
                        </div>

                        <ul className="tier-features">
                            {tier.features.map((feature, j) => (
                                <li key={j}>
                                    <span className="check">✓</span>
                                    {feature}
                                </li>
                            ))}
                        </ul>

                        <a
                            href={tier.ctaLink}
                            className={`btn ${tier.highlighted ? 'btn-primary' : 'btn-secondary'}`}
                            target="_blank"
                            rel="noopener noreferrer"
                        >
                            [ {tier.cta} ]
                        </a>
                    </div>
                ))}
            </div>

            <div className="tiers-note">
                <p>
                    <strong>Early Bird:</strong> Lifetime pricing available during launch.
                    Standard pricing will be $9/month or $79/year.
                </p>
            </div>
        </section>
    )
}
