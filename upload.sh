#!/bin/sh

touch ~/.dropbox_uploader

echo "APPKEY="$APPKEY >> ~/.dropbox_uploader
echo "APPSECRET="$APPSECRET >> ~/.dropbox_uploader
echo "ACCESS_LEVEL="$ACCESS_LEVEL >> ~/.dropbox_uploader
echo "OAUTH_ACCESS_TOKEN="$OAUTH_ACCESS_TOKEN >> ~/.dropbox_uploader
echo "OAUTH_ACCESS_TOKEN_SECRET="$OAUTH_ACCESS_TOKEN_SECRET >> ~/.dropbox_uploader

export curdate=`date "+%m-%d-%Y"`

#chmod +x dropbox_uploader.sh

cp ../Packages/KT747-AOSP-JB-MR2-3.4-VZW-$curdate.zip ../Packages/KT747-AOSP-JB-MR2-3.4-VZW-$curdate-DropBox.zip

./dropbox_uploader.sh ../Packages/KT747-AOSP-JB-MR2-3.4-VZW-$curdate-DropBox.zip Public/

#  - touch ~/.dropbox_uploader
#  - echo "APPKEY="$APPKEY >> ~/.dropbox_uploader
#  - echo "APPSECRET="$APPSECRET >> ~/.dropbox_uploader
#  - echo "ACCESS_LEVEL="$ACCESS_LEVEL >> ~/.dropbox_uploader
#  - echo "OAUTH_ACCESS_TOKEN="$OAUTH_ACCESS_TOKEN >> ~/.dropbox_uploader
#  - echo "OAUTH_ACCESS_TOKEN_SECRET="$OAUTH_ACCESS_TOKEN_SECRET >> ~/.dropbox_uploader
#  - export curdate=`date "+%m-%d-%Y"`
#  - cp ../Packages/KT747-AOSP-JB-MR2-3.4-VZW-$curdate.zip ../Packages/KT747-AOSP-JB-MR2-3.4-VZW-$curdate-DropBox.zip
#  - sh ./dropbox_uploader.sh ../Packages/KT747-AOSP-JB-MR2-3.4-VZW-$curdate-DropBox.zip Public/
