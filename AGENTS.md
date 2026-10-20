# Project EX - Agent Instructions

## Project Overview

Project EX is a PvE extraction shooter built in Unreal Engine 5.8.

The game focuses on tactical combat, looting, exploration,

progression, and cooperative multiplayer.

Refer to `GDD.md` for the game's design and intended features.  
  
As of 10/19/2026 there is no need for new branches. Just use main. 

## Technology

- Engine: Unreal Engine 5.8
- Language: C++ and Blueprints
- C++ for core gameplay systems and logic.
- Blueprints for visuals, UI, animation, and configuration.
- Design gameplay systems with multiplayer replication in mind.
- Prefer server-authoritative gameplay for multiplayer interactions.

## Development Guidelines

- Keep implementations simple, modular, and maintainable.
- Follow Unreal Engine conventions and existing project structure.
- Reuse existing systems instead of creating duplicates.
- Avoid unnecessary dependencies, plugins, or third-party libraries.
- Don't overengineer features or build systems we don't need yet.
- Implement features in small, testable increments.
- Ask before making major architectural changes.

## Working With the Project

- Read relevant existing code before modifying it.
- Check `GDD.md` when implementing gameplay features.
- Don't modify unrelated files.
- Don't delete or replace existing assets without approval.
- Don't modify engine source files.
- Keep C++ and Blueprint responsibilities clearly separated.
- Preserve compatibility with Unreal Engine 5.8.

## Testing and Communication

- Check for compilation errors when possible.
- Never claim something was tested unless it actually was.
- Explain any steps needed to test changes in Unreal Editor.
- Summarize what was changed and why.
- Flag potential problems or limitations.
- If requirements are unclear, ask rather than assume.

## Current Development Priorities

1. Establish core player movement and interactions.

Focus on the current task rather than implementing future features prematurely.

## Context Management

START OF A NEW TASK:

1. Read AGENTS.md.
2. Read docs/PROJECT_STATE.md.
3. Read docs/CODEBASE_MAP.md only when locating code.
4. Read docs/DECISIONS.md only when relevant.
5. Inspect only source files required for the task.
6. Do not assume previous chat context is available.

DURING DEVELOPMENT:

- Treat source code as authoritative when documentation conflicts with implementation.
- Avoid broad repository searches.
- Do not reread unchanged files.
- Do not generate unnecessary documentation.
- Do not perform unrelated refactoring.
- Do not modify maps unless explicitly requested.
- Preserve existing working functionality.

AFTER MEANINGFUL CHANGES:

- Update PROJECT_STATE.md.
- Update CODEBASE_MAP.md only when important classes or APIs change.
- Update DECISIONS.md only for new decisions.
- Keep documentation factual and concise.

WHEN CONTEXT IS RUNNING LOW:

1. Finish or safely stop the current operation.
2. Record completed work.
3. Record incomplete work.
4. Record relevant modified files.
5. Record known errors and blockers.
6. Record the exact next action.
7. Recommend continuing in a new conversation.

Do not begin another major task when context is nearly exhausted.

The agent cannot assume it will detect context exhaustion automatically. Maintain the project state after each meaningful task so context can be recovered at any time.

## AI Agent Efficiency

- Optimize for minimal tool calls and context usage.
- Read persistent documentation before exploring code.
- Inspect only task-relevant files.
- Avoid scanning generated Unreal directories.
- Avoid inspecting imported asset packs unless needed.
- Do not repeatedly read unchanged files.
- Do not produce extensive planning documents.
- Do not perform unrelated refactoring.
- Do not create unnecessary abstractions.
- Prefer existing classes and engine functionality.
- Avoid repeated compilation attempts.
- Keep final reports under 100 words.
- Update project documentation only when necessary.

These rules must not prevent required validation or cause incomplete implementation.