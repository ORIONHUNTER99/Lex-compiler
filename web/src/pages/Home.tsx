import { CodeTransformer } from '../components/CodeTransformer'
import { Hero, ProblemSolution, Stats, Install, Backends, Features, CTA, Tiers } from '../components/home'
import { useLanguage } from '../i18n/LanguageContext'

export default function Home() {
    const { t } = useLanguage()

    return (
        <div className="home-page">
            <Hero />

            <main>
                <ProblemSolution />

                <section className="teaser-section">
                    <div className="teaser-header">
                        <h2>{t('teaser.title')}</h2>
                        <p>{t('teaser.subtitle')}</p>
                    </div>
                    <div className="transformer-wrapper">
                        <CodeTransformer />
                    </div>
                </section>

                <Stats />
                <Install />
                <Backends />
                <Tiers />
                <Features />
                <CTA />
            </main>
        </div>
    )
}
