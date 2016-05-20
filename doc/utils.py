import asyncio



class LineReader:
	'''
	Use `async for line in LineReader(streamReader)` to iterate lines from a stream.
	'''

	def __init__(self, reader: asyncio.StreamReader) -> None:
		self._reader = reader


	async def __aiter__(self):
		return self


	async def __anext__(self) -> str:
		if self._reader.at_eof():
			raise StopAsyncIteration()
		while not self._reader.at_eof():
			line = (await self._reader.readline()).decode('utf-8').rstrip('\n')
			if line:
				return line
