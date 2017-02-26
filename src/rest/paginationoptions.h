#ifndef PAGINATIONOPTIONS_H
#define PAGINATIONOPTIONS_H

#include <AnaCloud/http/httprequest.h>

struct PaginationOptions
{
   PaginationOptions(HttpRequest &request, int maxLimit = 100){

       this->maxLimit = maxLimit;

       since = request.getParameter("since").toLongLong();
       limit = request.getParameter("limit").toInt();
       page = request.getParameter("page");
       before = request.getParameter("before");
       after = request.getParameter("after");

       if(limit > maxLimit) limit = maxLimit;
   }

   qint64 since; // last record timestamp
   int limit;
   int page;
   QByteArray before; // puul-to-refresh
   QByteArray after; // fetch more
   int maxLimit;
};

#endif // PAGINATIONOPTIONS_H
