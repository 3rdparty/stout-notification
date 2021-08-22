"""Dependency specific initialization."""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def deps(repo_mapping = {}):
    if "com_github_google_googletest" not in native.existing_rules():
        http_archive(
            name = "com_github_google_googletest",
            url = "https://github.com/google/googletest/archive/release-1.10.0.tar.gz",
            sha256 = "9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb",
            strip_prefix = "googletest-release-1.10.0",
            repo_mapping = repo_mapping,
        )