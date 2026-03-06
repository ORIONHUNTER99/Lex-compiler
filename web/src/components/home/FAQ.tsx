import { useState } from 'react'
import { useLanguage } from '../../i18n/LanguageContext'

export function FAQ() {
    const { t } = useLanguage()
    const [openIndex, setOpenIndex] = useState<number | null>(null)
    const items = t('faq.items') as unknown as { q: string, a: string }[]

    return (
        <section className="faq-section">
            <h2>{t('faq.title')}</h2>
            <div className="faq-list">
                {items.map((item, i) => (
                    <div
                        key={i}
                        className={`faq-item ${openIndex === i ? 'open' : ''}`}
                        onClick={() => setOpenIndex(openIndex === i ? null : i)}
                    >
                        <div className="faq-question">
                            <span>{item.q}</span>
                            <span className="faq-toggle">{openIndex === i ? '-' : '+'}</span>
                        </div>
                        {openIndex === i && (
                            <div className="faq-answer">
                                <p>{item.a}</p>
                            </div>
                        )}
                    </div>
                ))}
            </div>
        </section>
    )
}
