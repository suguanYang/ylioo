```
declare namespace wx {
  namespace request {
    type Param = {
      url: string;
      data?: any | string | ArrayBuffer;
      header?: any;
      method?: string;
      dataType?: string;
      responseType?: string;
      success?: ParamPropSuccess;
      fail?: ParamPropFail;
      complete?: ParamPropComplete;
    };

    type ParamPropSuccess = (res: ParamPropSuccessParam) => any;
    type ParamPropSuccessParam = {
      data: any | string | ArrayBuffer;
      statusCode: number;
      header: any;
    };

    type ParamPropFail = (err: any) => any;

    type ParamPropComplete = () => any;
    type Return = {
      abort: ReturnPropAbort;
    };
    type ReturnPropAbort = () => any;
  }

  function request(OBJECT: request.Param): request.Return;
}
```
