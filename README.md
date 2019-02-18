# Starter Kit for Rust on the back-end and Reason on the front-end

## Rocket v0.4

Rocket still requires nightly, at least until v0.5. After cloning this repo, don't forget to

```
cd /path/to/api-rust
rustup override set nightly
```

## Database URL and secrets

To ensure we don't keep your secrets in the database, we don't keep the Rocket.toml file in the repository. Instead there is a Rocket.sample.toml file for you to edit.
