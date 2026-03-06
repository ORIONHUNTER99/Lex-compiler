import { createContext, useContext, useState } from 'react';
import type { ReactNode } from 'react';
import { en } from './locales/en';
import { it } from './locales/it';
import type { Translations } from './types';

type Language = 'en' | 'it';

interface LanguageContextType {
    language: Language;
    setLanguage: (lang: Language) => void;
    t: (key: string) => string;
}

const dictionaries: Record<Language, Translations> = { en, it };

const LanguageContext = createContext<LanguageContextType | undefined>(undefined);

export function LanguageProvider({ children }: { children: ReactNode }) {
    // Try to load from localStorage, fallback to browser language or 'en'
    const [language, setLanguageState] = useState<Language>(() => {
        const saved = localStorage.getItem('lex_lang') as Language;
        if (saved && (saved === 'en' || saved === 'it')) return saved;

        const browserLang = navigator.language.split('-')[0];
        return browserLang === 'it' ? 'it' : 'en';
    });

    const setLanguage = (lang: Language) => {
        setLanguageState(lang);
        localStorage.setItem('lex_lang', lang);
    };

    // Helper function to resolve dot-notated keys like 'hero.tagline'
    const t = (path: string): string => {
        const keys = path.split('.');
        let current: any = dictionaries[language];

        for (const key of keys) {
            if (current[key] === undefined) {
                console.warn(`Translation key missing: ${path}`);
                return path;
            }
            current = current[key];
        }

        return current as string;
    };

    return (
        <LanguageContext.Provider value={{ language, setLanguage, t }}>
            {children}
        </LanguageContext.Provider>
    );
}

export function useLanguage() {
    const context = useContext(LanguageContext);
    if (context === undefined) {
        throw new Error('useLanguage must be used within a LanguageProvider');
    }
    return context;
}
