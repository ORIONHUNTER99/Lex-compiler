import { useLanguage } from '../../i18n/LanguageContext';

export function ProblemSolution() {
    const { t } = useLanguage();

    return (
        <section className="problem-solution-section">
            <div className="split-view">
                <div className="split-panel bad">
                    <div className="panel-header">
                        <span className="dot red"></span>
                        <span>{t('problem.badTitle')}</span>
                    </div>
                    <pre className="mock-code">
                        {`"items": {
  "sword_01": {
    "type": "weapon",
    "damage": 50,
    "durability": 100,
    "effects": ["bleeding"] // Easy to typo
  }
}`}
                    </pre>
                </div>

                <div className="split-panel good">
                    <div className="panel-header">
                        <span className="dot green"></span>
                        <span>{t('problem.goodTitle')}</span>
                    </div>
                    <pre className="mock-code">
                        {`item sword_01 {
  type: weapon
  damage: 50
  durability: 100
  effects: [bleeding]
}`}
                    </pre>
                </div>
            </div>
        </section>
    )
}
