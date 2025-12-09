# Gemini Agent Development Guidelines

This document provides guidelines for the Gemini agent to follow when working on this project. Adherence to these guidelines is crucial for maintaining code quality, ensuring project consistency, and enabling efficient development.

## 1. Core Principles

- **Modularity:** The project must be structured in a modular way. Prefer creating multiple small, single-responsibility files and classes over large, monolithic ones. This improves readability, testability, and maintainability.
- **Token Efficiency:** Write clear and concise code. Avoid unnecessary verbosity or comments that state the obvious. Focus on self-documenting code.
- **User-Centric:** The build process and project management should be as simple as possible for the end-user. We will use CMake for this purpose. When uncertain about a feature or implementation detail, ask for user input.

## 2. Environment and Tooling

### Build System
- This project uses **CMake**. All build configurations should be managed through `CMakeLists.txt` files. The build directory (`build/`) is ignored by Git.

### Package Management
- The agent is permitted to manage system packages on Arch Linux using `pacman`, `paru`, or `yay`.
- Dependencies can also be compiled from source if necessary.
- Before installing any package, inform the user of the command you intend to run.

### Git and Version Control
- **Repository:** You are working in a new Git repository on the user's machine.
- **Configuration:** Use the GitHub CLI (`gh`) for any necessary Git or repository configuration.
- **Commits:** Commit changes **frequently**. Each commit should represent a small, logical unit of work. A good cadence is after implementing any distinct feature or fix.
- **Pushing:** Push commits to the remote repository **often**. This ensures there is always a backup and allows for easy rollbacks by you or the user.

### Execution and Testing
- **Do not run the executable directly.** If user testing is required for a feature that cannot be tested programmatically, end your output and wait for the user to test and report back.

## 3. Dependencies
- **Qt:** The project will use the Qt framework (Qt6).
- **projectM:** The projectM visualization library will be integrated using CMake's `FetchContent` feature.

## 4. Available Resources

- You have access to all `gemini-cli` capabilities.
- You can utilize any available packages already installed on the user's system.
- You can interact with any available MCP (Multi-Capability Peripheral) servers.

## 5. References and example code

- the reference_code directory is git ignored but if you set false to respecting this gitignore then you may investigate previous user work and external projecfts for inspiration or items such as proper API usage.
- The MiniMax agentic coding model, one of the current best, has thorough documentation (ignore the codebase largely; never compiled properly) in mdarkdown md files inside of reference_code/vibe-sync

By following these instructions, you will help create a high-quality, maintainable, and user-friendly C++ application.
