import { useState } from 'react'
import { installCommands } from './data'
import { useLanguage } from '../../i18n/LanguageContext'

export function Install() {
    const [installTab, setInstallTab] = useState<'windows' | 'unix' | 'source'>('windows')
    const { t } = useLanguage()

    return (
        <section className="install-section">
            <h2>{t('install.title')}</h2>
            <div className="install-tabs">
                <button
                    className={installTab === 'windows' ? 'active' : ''}
                    onClick={() => setInstallTab('windows')}
                >
                    {t('install.win')}
                </button>
                <button
                    className={installTab === 'unix' ? 'active' : ''}
                    onClick={() => setInstallTab('unix')}
                >
                    {t('install.unix')}
                </button>
                <button
                    className={installTab === 'source' ? 'active' : ''}
                    onClick={() => setInstallTab('source')}
                >
                    {t('install.src')}
                </button>
            </div>
            <div className="install-code">
                {installCommands[installTab]}
            </div>
        </section>
    )
}
