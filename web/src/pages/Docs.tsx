import { useState, useEffect } from 'react';
import { Routes, Route, Link, useLocation, useParams } from 'react-router-dom';
import ReactMarkdown from 'react-markdown';
import remarkGfm from 'remark-gfm';
import Prism from 'prismjs';

// Markdown fetcher mapping
const DOC_MAP: Record<string, string> = {
    'intro': 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/README.md',
    'api': 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/docs/API_REFERENCE.md',
    'tutorial': 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/docs/TUTORIAL.md',
    'godot': 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/docs/INTEGRATION_GODOT.md',
    'unity': 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/docs/INTEGRATION_UNITY.md',
    'love2d': 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/docs/INTEGRATION_LOVE2D.md',
    'roadmap': 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/docs/ROADMAP.md',
};

function MarkdownViewer({ docKey }: { docKey: string }) {
    const [content, setContent] = useState<string>('> [ SYS.CONNECTING ] Loading encrypted databanks...');

    useEffect(() => {
        let url = DOC_MAP[docKey] || DOC_MAP['intro'];

        fetch(url)
            .then(res => {
                if (!res.ok) throw new Error('Data breach: unable to fetch document.');
                return res.text();
            })
            .then(text => {
                // Simple fix for relative image links in README
                const processed = text.replace(/docs\/assets\//g, 'https://raw.githubusercontent.com/David-Imperium/Lex-compiler/master/docs/assets/');
                setContent(processed);
            })
            .catch(err => setContent(`> [ ERROR ] ${err.message}`));
    }, [docKey]);

    useEffect(() => {
        // Re-run prism highlighting when content changes
        setTimeout(() => {
            Prism.highlightAll();
        }, 50);
    }, [content]);

    return (
        <div className="markdown-body">
            <ReactMarkdown remarkPlugins={[remarkGfm]}>
                {content}
            </ReactMarkdown>
        </div>
    );
}

function DocRouteWrapper() {
    const { docId } = useParams<{ docId: string }>();
    return <MarkdownViewer docKey={docId || 'intro'} />;
}

export default function Docs() {
    const location = useLocation();

    const isActive = (path: string) => location.pathname === path ? 'active' : '';

    return (
        <div className="docs-layout">
            <aside className="docs-sidebar">
                <h3 className="sidebar-title">Main_Index</h3>
                <nav className="sidebar-nav">
                    <Link to="/docs" className={location.pathname === '/docs' ? 'active' : ''}>Introduction</Link>
                    <Link to="/docs/tutorial" className={isActive('/docs/tutorial')}>Quick Start Tutorial</Link>
                    <Link to="/docs/api" className={isActive('/docs/api')}>API Reference</Link>
                    <Link to="/docs/roadmap" className={isActive('/docs/roadmap')}>System Roadmap</Link>
                </nav>

                <h3 className="sidebar-title mt-6">Integrations</h3>
                <nav className="sidebar-nav">
                    <Link to="/docs/godot" className={isActive('/docs/godot')}>[ GDS ] Godot Node</Link>
                    <Link to="/docs/unity" className={isActive('/docs/unity')}>[ C#_ ] Unity Object</Link>
                    <Link to="/docs/love2d" className={isActive('/docs/love2d')}>[ LV2 ] LÖVE Module</Link>
                </nav>
            </aside>

            <main className="docs-content">
                <Routes>
                    <Route path="/" element={<MarkdownViewer docKey="intro" />} />
                    <Route path="/:docId" element={<DocRouteWrapper />} />
                </Routes>
            </main>
        </div>
    );
}
