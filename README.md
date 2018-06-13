# Add feeds
    
    echo 'src-git rtty https://github.com/zhaojh329/rtty.git;openwrt-14.04' >> feeds.conf.default

# Update feeds

    ./scripts/feeds uninstall -a
    ./scripts/feeds update rtty
    ./scripts/feeds install -a -f -p rtty
    ./scripts/feeds install -a

# Select rtty in menuconfig and compile new image.

	Utilities  --->
    	Terminal  --->
        	<*> rtty-polarssl............................ A reverse proxy WebTTY (polarssl)
        	< > rtty-nossl............................... A reverse proxy WebTTY (NO SSL)
        	< > rtty-openssl............................ A reverse proxy WebTTY (openssl)
        	< > rtty-cyassl............................ A reverse proxy WebTTY (cyassl)
