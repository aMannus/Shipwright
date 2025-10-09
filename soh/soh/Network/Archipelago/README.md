# Archipelago Integration

## todo
document stuff

## Cert stores and `.pem` files

[`apclientpp` suggests](https://github.com/black-sliver/apclientpp?tab=readme-ov-file#ssl-support)
> * to make certificate verifaction work cross-platform
>   * include a cert store file and its license, e.g. [curl's CA Extract](https://curl.se/docs/caextract.html)
>   * load the cert store by passing the path as 4th argument to APClient's constructor
> * apclient will try to load system certs, but this should only be used for testing: outdated Windows has outdated certs, macos/Linux without OpenSSL or with a different version won't find any certs

Connecting using system certs has seemed to work just fine, so for the initial implementation we've decided to temporarily go against the "this should only be used for testing" advice.

An ideal implementation would:
* Use `libcurl` to download a cert from CA Extract at runtime before initializing the `APClient`
  * This would be done with the `libcurl` c-code equivalent of `curl --etag-compare etag.txt --etag-save etag.txt --remote-name https://curl.se/ca/cacert.pem`
* Use the downloaded cert when initializing `APClient`
