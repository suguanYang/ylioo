Netflix video distribution has two major components: the Amazon cloud and its own private CDN infrastructure.
## Content ingestion. 
Before Netflix can distribute a movie to its customers, it must
first ingest and process the movie. Netflix receives studio master versions of
movies and uploads them to hosts in the Amazon cloud.
## Content processing. 
The machines in the Amazon cloud create many different
formats for each movie, suitable for a diverse array of client video players run-
ning on desktop computers, smartphones, and game consoles connected to televi-
sions. A different version is created for each of these formats and at multiple bit
rates, allowing for adaptive streaming over HTTP using DASH.
## Uploading versions to its CDN. 
Once all of the versions of a movie have been
created, the hosts in the Amazon cloud upload the versions to its CDN.
Netflix distributes by pushing the videos to its CDN servers during off-peak hours

Similar to Netflix, Google uses its own private CDN
to distribute YouTube videos, and has installed server clusters in many hundreds
of different IXP and ISP locations. From these locations and directly from its huge
data centers, Google distributes YouTube videos [Adhikari 2011a]. Unlike Netflix,
however, Google uses pull caching, and DNS redirect,. Most of the time, Google’s cluster-selection strategydirects the client to the cluster for which the RTT between client and cluster is the lowest; however, in order to balance the load across clusters, sometimes the client is directed (via DNS) to a more distant cluster [Torres 2011].
 <!-- The DNS server provides api to UPDATE and DELTE records, this can help to make the records responds to the real time measurements more frequently -->

 Several million videos are uploaded to YouTube every day. Not only are You-
Tube videos streamed from server to client over HTTP, but YouTube uploaders also
upload their videos from client to server over HTTP. YouTube processes each video
it receives, converting it to a YouTube video format and creating multiple versions
at different bit rates. This processing takes place entirely within Google data centers