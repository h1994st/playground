# VPS Configuration

VPS Provider: DigitalOcean

## SSH

1. Prepare SSH key on your own machine

    ```bash
    ssh-keygen -t ed25519 -C <comment>
    # Generate: `id_ed25519`, `id_ed25519.pub`
    ```

2. Add `id_ed25519.pub` to `.ssh/authorized_keys` on VPS

    ```bash
    ssh-copy-id <username>@<remote vps>
    ```

3. Copy authorized keys of `root` to the newly created user (see below)

    ```bash
    rsync --archive --chown=<username>:<username> ~/.ssh /home/<username>
    ```

4. Update SSH configuration: `/etc/ssh/sshd_config`

    ```txt
    Port <not 22>
    PermitRootLogin no
    PubkeyAuthentication yes
    PasswordAuthentication no
    PermitEmptyPasswords no
    ```

5. Restart SSH server

    ```bash
    sudo systemctl restart ssh
    ```

## New User

```bash
adduser <username>

# Grant administrative privileges
usermod -aG sudo <username>
```

## Firewall

(TBD)

> Ubuntu 22.04 servers can use the UFW firewall to ensure only connections to
certain services are allowed
>
> Reference: [Step 4 — Setting Up a Firewall](https://www.digitalocean.com/community/tutorials/initial-server-setup-with-ubuntu-22-04#step-4-setting-up-a-firewall)

## Tools

```bash
sudo apt update
sudo apt install vim git zsh

# Oh My Zsh
sh -c "$(wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)"
# Theme: jonathan
# Plugin: git

# Vim
sh -c "$(wget https://raw.githubusercontent.com/h1994st/interesting-scripts/master/sync-vim-conf.sh -O -)"
# NOTE: `ctags` installation may result in errors
# Try `sudo apt install universal-ctags` instead
```
