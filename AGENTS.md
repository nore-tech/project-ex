# Project EX - Agent Instructions

## Project Overview

Project EX is a PvE extraction shooter built in Unreal Engine 5.8.

The game focuses on tactical combat, looting, exploration,

progression, and cooperative multiplayer.

Refer to `GDD.md` for the game's design and intended features.

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