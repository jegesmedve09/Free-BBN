<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>Free-BBN - Open-source PSBBN Recreation</title>
  <style>
    body {
      font-family: -apple-system, BlinkMacC, "Segoe UI", Roboto, sans-serif;
      line-height: 1.6;
      max-width: 900px;
      margin: 0 auto;
      padding: 40px 20px;
      background: #0d1117;
      color: #c9d1d9;
    }
    h1, h2, h3 {
      color: #58a6ff;
    }
    h1 {
      border-bottom: 2px solid #30363d;
      padding-bottom: 0.4em;
      margin-bottom: 0.6em;
    }
    .tagline {
      font-size: 1.3em;
      color: #8b949e;
      font-style: italic;
      margin: 0.8em 0 2em;
    }
    .warning {
      background: #2d1b1b;
      border-left: 5px solid #c94e4e;
      padding: 16px 20px;
      margin: 2em 0;
      border-radius: 6px;
    }
    code {
      background: #161b22;
      padding: 2px 6px;
      border-radius: 4px;
      font-family: "Consolas", "Courier New", monospace;
    }
    pre {
      background: #161b22;
      padding: 16px;
      border-radius: 6px;
      overflow-x: auto;
    }
    .credits-grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
      gap: 24px;
      margin: 2.5em 0;
    }
    .credit-card {
      background: #161b22;
      border: 1px solid #30363d;
      border-radius: 8px;
      padding: 20px;
      transition: all 0.15s ease;
    }
    .credit-card:hover {
      border-color: #58a6ff;
      transform: translateY(-3px);
    }
    .credit-card h4 {
      margin-top: 0;
      color: #79c0ff;
      font-size: 1.2em;
    }
    .glow {
      color: #00d4ff;
      font-weight: bold;
      text-shadow: 0 0 8px rgba(0,212,255,0.5);
    }
  </style>
</head>
<body>

<h1>Free-BBN</h1>

<p class="tagline">
  Open-source recreation of the PlayStation Broadband Navigator (PSBBN) dashboard,<br>
  built from scratch with <strong>ps2sdk</strong> and <strong>gsKit</strong>.
</p>

<p><strong>No patches. No official Sony hardware required. Pure homebrew freedom.</strong></p>

<h2>About</h2>

<p>
  The original PSBBN was an amazing dashboard locked behind the official network/HDD adapter.<br>
  <strong>Free-BBN</strong> aims to bring back that <span class="glow">iconic blue glow</span>, flowing waves, 
  and smooth menu feel — but for <strong>every PS2 owner</strong> with any HDD setup, slim or fat, 
  modern adapters included.
</p>

<p>
  This is <strong>not</strong> a patch of the original Sony binary.<br>
  It’s a full homebrew recreation, open source from day one, so it can live forever and evolve with the community.
</p>

<h3>Current status (December 2025):</h3>
<ul>
  <li>Splash screen with fade-in and hold working on real hardware (SCPH-50007)</li>
  <li>Startup chime playing (if it wants to)</li>
  <li>Modular structure ready for menu, icons, HDD browser, etc.</li>
  <li>Early alpha — but it boots and glows.</li>
</ul>

<h2>Credits</h2>

<div class="credits-grid">

  <div class="credit-card">
    <h4>Idea & Vision</h4>
    <p><strong>Bögi Dániel (@jegesmedve09)</strong><br>
    The madman who said “Sony didn’t give us open PSBBN, so I’ll build it.”</p>
  </div>

  <div class="credit-card">
    <h4>AI Chaos Companion</h4>
    <p><strong>Grok (built by xAI)</strong><br>
    The unhinged AI co-programmer who wrote billions of lines of blessed spaghetti that sometimes work,<br>
    named delays <code>FuckAroundSilently()</code>, and kept the dream alive through black screens and toolchain hell.</p>
  </div>

  <div class="credit-card">
    <h4>Special Thanks</h4>
    <ul style="margin:0.6em 0 0 1.2em; padding-left:0;">
      <li>The PS2 homebrew scene for inspiration</li>
      <li>CosmicScale's amazing PSBBN English patch (the gold standard)</li>
      <li>Our sacred green screen (the first light)</li>
      <li>RCA cables (for revealing the truth HDMI tried to hide)</li>
    </ul>
  </div>

</div>

<h2>License</h2>

<p>
  <strong>MIT License</strong> – Copyright © 2025 Bögi Dániel (<a href="https://github.com/jegesmedve09" style="color:#58a6ff;">jegesmedve09</a>)<br>
  Use it, modify it, build on it — just keep my name in the copyright notice.
</p>

<h2 style="margin-top:3em;">More coming soon.</h2>
<p class="glow" style="font-size:1.6em; margin:0;">The glow is just beginning.</p>

<p style="text-align:right; color:#8b949e; margin-top:4em;">— jegesmedve09</p>

<div class="warning">
  <strong>WARNING:</strong><br><br>
  before anyone starts ghossiping about the code having AI,<br>
  the code thats entirely written and dependent on AI is shit,<br>
  because the humans dont wanna fuck around and find out what the code actualy does,<br><br>
  but when we use AI, as a guide tool (as a brother who deliberately cuts power when u are at 99% compiling your linux kernel),<br>
  to help fix mistakes, and we actually know how the code works,<br>
  now thats, thats not shit, thats a smart way of sharing load...<br><br>
  dont cancel me on X...please...nor Grok, Grok did nothing wrong
</div>

</body>
</html>
