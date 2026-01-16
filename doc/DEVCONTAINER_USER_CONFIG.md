# DevContainer User Configuration

## Why Root Was Used Initially

The DevContainer was initially configured to run as `root` because:

1. **Package Installation**: The setup script needed to install system packages, which requires root privileges
2. **Simplified Permissions**: Running as root avoided permission issues with file ownership and access
3. **Quick Setup**: No need to configure sudo permissions or user switching

## Why This Was Changed

Running as root in DevContainers is **not recommended** for several reasons:

### Security Concerns
- **Principle of Least Privilege**: Applications should run with minimal necessary permissions
- **Container Security**: Root access in containers can be a security risk
- **Best Practices**: DevContainer documentation recommends using non-root users

### Development Best Practices
- **File Ownership**: Files created as root may have incorrect ownership
- **Permission Issues**: Some tools expect to run as non-root users
- **Consistency**: Matches production environments where applications typically run as non-root

## Current Configuration

The DevContainer now uses the **`vscode` user** as the default:

```json
{
    "remoteUser": "vscode"
}
```

### How It Works

1. **Initial Setup (Root)**: The `postCreateCommand` runs as root to install system packages
2. **User Creation**: The setup script creates the `vscode` user with sudo privileges
3. **Permission Setup**: Workspace files are owned by the `vscode` user
4. **Development (vscode)**: All development work happens as the `vscode` user

### Benefits

- ✅ **Security**: Non-root user for development
- ✅ **Compatibility**: Works with tools that expect non-root users
- ✅ **Best Practices**: Follows DevContainer recommendations
- ✅ **Flexibility**: Can still install packages when needed via sudo

## Usage

### For Package Installation
When you need to install packages, the scripts automatically detect the user:

```bash
# Works as both root and vscode user
make setup
```

### For Development
All development commands work as the `vscode` user:

```bash
make build    # Build the project
make run      # Run the game
make test     # Run tests
```

## Migration Notes

If you were previously using the container as root:

1. **Rebuild Container**: The user change requires a container rebuild
2. **File Permissions**: Existing files will be automatically fixed by the setup script
3. **No Code Changes**: All existing commands work the same way

## Troubleshooting

### Permission Issues
If you encounter permission issues:

```bash
# Fix workspace permissions
sudo chown -R vscode:vscode /workspaces/Chinese-chess
```

### Package Installation
If you need to install packages manually:

```bash
# The vscode user has sudo privileges
sudo apt-get install <package-name>
```

## Summary

The DevContainer now follows security best practices by:
- Using the `vscode` user for development
- Running initial setup as root only when necessary
- Providing sudo access for package management
- Maintaining compatibility with all existing workflows


