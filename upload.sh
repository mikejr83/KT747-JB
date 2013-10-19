#!/usr/bin/env bash
touch ~/.dropbox_uploader

echo "APPKEY="$APPKEY >> ~/.dropbox_uploader
echo "APPSECRET="$APPSECRET >> ~/.dropbox_uploader
echo "ACCESS_LEVEL="$ACCESS_LEVEL >> ~/.dropbox_uploader
echo "OAUTH_ACCESS_TOKEN="$OAUTH_ACCESS_TOKEN >> ~/.dropbox_uploader
echo "OAUTH_ACCESS_TOKEN_SECRET="$OAUTH_ACCESS_TOKEN_SECRET >> ~/.dropbox_uploader

chmod +x dropbox_uploader.sh

sh ./dropbox_uploader.sh ../Packages/KT747* Public/
