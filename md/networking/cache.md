---
title: "How we Cache?"
---

Network cache is a mechanism that allows a browser to store responses from web servers in a local cache. This cache can be used to reduce the number of requests made to the server, and can improve the performance of a website.

In Browser, we can cache 

1. HTTP Cache
2. In Memory Cache
3. Disk Cache(persistent cache)






### weak cache

### strong cache

### local CDN

### service worker

### the query string

### distributed storage

### clear site data


## Cache in Micro-Frontend
In Micro-Frontend, applications usually publish their own assets, which means their entry points are different,
its hard to share a same cache key for all the applications, they have differernt content, different versions.
one way to solve this is: when application publising, we need to generate a differernt key, which make sure the cached key
will not be used at client side. but this has limitation since the client must know the key before it can be used, if the key is
URL, the client that use the same URL will not be able to get the new content, if before the user load the content, they must request a new API to check
whether the key is updated, why we need cache?

Another way is to let the client update the cache automatically, they can update the cache when they get a 'update' event from the server.
the also can query te content after the content is loaded at background, but all of these can not grantuee the cache can be updated in time.

A compromised way is to make all applications have the same entry ponit, and make it small as possible, the client will always get the latest entry point,
the entry point is just like a conent loader with refreshed cache key for each content the application has. 

And if we update the entry point address once the application is published, the client can safly and easily get the latest content, because they know
the application they visit is the latest one, but this have to make sure the users are aware of the updates and the entry point's relationship.
If the entry point is just a URL, the user should recongnize this more easily, but if the entry point is just an address of a js files or other things
the user can not easily control or even acknowledge it. the system modules that responsible for load the applications have to update the entry point address
before the user visit the application or let the user know the application they visted is a outdated one otherwise this may led a misleading.


## Frontend and Backend versioning